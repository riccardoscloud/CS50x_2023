import os
import openai

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, password_check

openai.api_key = os.getenv("OPENAI_API_KEY")
openai.Model.list()

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///project.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    # Simple GET page, with content displayed conditionally of session
    return render_template("/index.html")


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
        
        # Ensure password is secure
        check = password_check(request.form.get("password"))
        if not check["password_ok"]:
            return apology("password needs min 10 characters, 1 digit, 1 symbol, 1 lower and 1 uppercase letter", 400)

        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # Redirect user to home page
        return redirect("/login")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")
    

@app.route("/generate", methods=["GET", "POST"])
@login_required
def generate():
    
    INTERESTS = ["History, Culture and Arts", "Outdoor and Nature", "Food and Dining", "Shopping", "Entertainment and Nightlife", "Sports and Adventure", "Religious and Spiritual Interests", "Family-Friendly Activities", "Wellness and Relaxation"]
    
    if request.method == "POST":

        # Extract variables
        destination = request.form.get("destination")
        start_date = request.form.get("start_date")
        end_date = request.form.get("end_date")
        interests = request.form.getlist("interests")
        
        # Input validation
        if not interests:
            return apology("you must select at least one interest", 400)
        
        # Extract variables
        interests_list = ""
        for i in interests:
            
            # Input validation
            if i not in INTERESTS:
                return apology("do not mess with the code please", 400)
            
            # Extract variables
            interests_list += i + ", "
        interests_list = interests_list.rstrip(", ")

        # Input validation
        if not destination:
            return apology("you must input a destination", 400)
        
        if not start_date or not end_date:
            return apology("you must input arrival and departure dates", 400)
        
        if start_date >= end_date:
            return apology("your departure date must be after the arrival date", 400)
        


        # Prompt generation
        PROMPT = f"Destinations are: {destination},\n arrival is: {start_date},\n \
                    departure is: {end_date},\n interests are: {interests_list}"
        
        PROMPT_NEW = f"Please provide me with personalized advice for my next holiday to {destination}.\
                        I will be there between {start_date} and {end_date}.\
                        My interests are: {interests}.\
                        The advice should be structured as follows:\
                        1. A first paragraph with general advice regarding {destination}, must-view places and hidden gems.\
                        2. One paragraph for each of the interests I've expressed, with each destination on a seperate bullet point, for example:\
                        Shopping, brief introduction about shopping in {destination}.\
                        - relevant shopping place #1, description;\
                        - relevant shopping place #2, description;\
                        - etc..\
                        3. A final paragraph with a proposed schedule for my trip, which must be relevant to my interests.\
                        All of the above should also be relevant to the moment of the year I'm visiting.\
                        For example you would suggest attending the cherry trees blossom if I were to go to Tokio at the end of March."

        completion = openai.ChatCompletion.create(
            model="gpt-3.5-turbo",
            messages=[
                {"role": "system", "content": "You are Cicero, an experienced travel guide who has visited the whole world. Use a professional, but friendly tone."},
                {"role": "user", "content": f"{PROMPT_NEW}"}
            ]
        )

        OUTPUT = completion.choices[0].message

        # Can do without additional app?
        return render_template("/output.html", output=OUTPUT)

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        return render_template("/generate.html", interests=INTERESTS)


@app.route("/faq")
def faq():
    # Simple GET page
    return render_template("/faq.html")