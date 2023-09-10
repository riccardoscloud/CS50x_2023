import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Initialize dict for portfolio
    PORTFOLIO = {}

    # Initialize grand total
    PORTFOLIO_VALUE = 0

    # Current user balance
    BALANCE = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']

    # Pull all transactions from current user
    rows = db.execute("SELECT stock, shares_quantity FROM purchases WHERE user_id = ?", session["user_id"])

    # Initialize a dict for each new symbol
    for row in rows:
        stock_name = row['stock']
        if stock_name not in PORTFOLIO:
            PORTFOLIO[stock_name] = {}
            PORTFOLIO[stock_name]['units'] = 0
            PORTFOLIO[stock_name]['price'] = lookup(stock_name)['price']
            PORTFOLIO[stock_name]['total_value'] = 0
        # Add line quantity
        PORTFOLIO[stock_name]['units'] += row['shares_quantity']

    # Calculate total value
    for stock in PORTFOLIO:
        PORTFOLIO[stock]['total_value'] = PORTFOLIO[stock]['units'] * PORTFOLIO[stock]['price']
        PORTFOLIO_VALUE += PORTFOLIO[stock]['total_value']
        # Convert to usd
        PORTFOLIO[stock]['price'] = usd(PORTFOLIO[stock]['price'])
        PORTFOLIO[stock]['total_value'] = usd(PORTFOLIO[stock]['total_value'])

    GRAND_TOTAL = usd(BALANCE + PORTFOLIO_VALUE)
    BALANCE = usd(BALANCE)
    PORTFOLIO_VALUE = usd(PORTFOLIO_VALUE)

    # Render index.html
    return render_template("/index.html", portfolio=PORTFOLIO, portfolio_value=PORTFOLIO_VALUE, balance=BALANCE, grand_total=GRAND_TOTAL)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Checks symbol input and that it does match existing stock
        if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("invalid symbol", 400)

        # Check input is an int
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("shares must be an integer", 400)

        # Shares quantity must be at least 1
        if int(request.form.get("shares")) < 1:
            return apology("you need to purchase at least 1 share", 400)

        # Calculate transaction details
        stock_price = lookup(request.form.get("symbol"))['price']
        transaction_price = stock_price * int(request.form.get("shares"))
        current_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
        new_balance = current_balance - transaction_price

        # Apologize for insufficient funds
        if current_balance < transaction_price:
            return apology("insufficient funds in balance", 403)

        # Update databases
        db.execute("INSERT INTO purchases (user_id, stock, shares_price, shares_quantity) VALUES (?, ?, ?, ?)", session["user_id"], request.form.get("symbol").upper(), stock_price, request.form.get("shares"))
        db.execute("UPDATE users SET cash= ? WHERE id = ?", new_balance, session["user_id"])

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Pull list of all transactions from current user
    LEDGER = db.execute("SELECT stock, shares_price, shares_quantity, timestamp FROM purchases WHERE user_id = ?", session["user_id"])

    return render_template("history.html", ledger=LEDGER)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("invalid symbol", 400)

        QUOTE = lookup(request.form.get("symbol"))
        QUOTE['price'] = usd(QUOTE['price'])
        return render_template("quoted.html", quote=QUOTE)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username doesn't exist
        if len(rows) > 0:
            return apology("username already exists", 400)

        # Ensure password was submitted
        if not request.form.get("password") or request.form.get("password") != request.form.get("confirmation"):
            return apology("must provide two matching passwords", 400)

        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Initialize portfolio
        PORTFOLIO = {}

        # Pull all transactions from current user
        rows = db.execute("SELECT stock, shares_quantity FROM purchases WHERE user_id = ?", session["user_id"])

        # Initialize a dict for each new symbol
        for row in rows:
            stock_name = row['stock']
            if stock_name not in PORTFOLIO:
                PORTFOLIO[stock_name] = 0
            # Add line quantity
            PORTFOLIO[stock_name] += row['shares_quantity']

        # Checks symbol input and that it does match existing stock
        if not request.form.get("symbol") or request.form.get("symbol") not in PORTFOLIO:
            return apology("invalid symbol", 400)

        # Check input is an int
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("shares must be an integer", 400)

        # Shares quantity must be at least 1
        if int(request.form.get("shares")) < 1 or int(request.form.get("shares")) > PORTFOLIO[request.form.get("symbol")]:
            return apology("number of shares error", 400)

        # Calculate transaction details
        stock_price = lookup(request.form.get("symbol"))['price']
        sold_shares = - (int(request.form.get("shares")))
        transaction_price = stock_price * sold_shares
        current_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
        new_balance = current_balance - transaction_price

        # Update databases
        db.execute("INSERT INTO purchases (user_id, stock, shares_price, shares_quantity) VALUES (?, ?, ?, ?)", session["user_id"], request.form.get("symbol").upper(), stock_price, sold_shares)
        db.execute("UPDATE users SET cash= ? WHERE id = ?", new_balance, session["user_id"])

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        # Initialize portfolio
        PORTFOLIO = {}

        # Pull all transactions from current user
        rows = db.execute("SELECT stock, shares_quantity FROM purchases WHERE user_id = ?", session["user_id"])

        # Initialize a dict for each new symbol
        for row in rows:
            stock_name = row['stock']
            if stock_name not in PORTFOLIO:
                PORTFOLIO[stock_name] = 0
            # Add line quantity
            PORTFOLIO[stock_name] += row['shares_quantity']

        return render_template("sell.html", portfolio=PORTFOLIO)


@app.route("/topup", methods=["GET", "POST"])
@login_required
def topup():
    """Top up cash balance"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Validate for positive input only
        if int(request.form.get("amount")) < 1:
            return apology("you can only add money", 403)

        # Get values
        current_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
        topup_amount = int(request.form.get("amount"))
        new_balance = current_balance + topup_amount

        # Update databases
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])
        db.execute("INSERT INTO topups (user_id, old_balance, topup_value, new_balance) VALUES (?, ?, ?, ?)", session["user_id"], current_balance, topup_amount, new_balance)

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        return render_template("topup.html")