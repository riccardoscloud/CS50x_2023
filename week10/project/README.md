# CICERO - The travel assistant

#### Video Demo:  <https://youtu.be/u_lHFQZ8v70>

#### Description:

Cicero is a travel assistant **powered by ChatGPT's API**.
It provides reccomendations on your upcoming trip, based on **where** you're going, **when**, **for how long**, and **what your interests are**.
It is implemented as a **website running on Flask**. It includes: **Python, SQL, HTML and CSS**.

-------------------------------------------------------------------------------------------------------------------------------------------------

**Session**

Cicero builds on top of Finance's skeleton.
The login, logout and register dynamics remain the same, with the addition of a password complexity check implemented as a *password_check(password)* function in *helpers.py*.

The *generate() page logic* introduces most of the complexity:

**UI**

Building on top of Finance's basics, I've used Bootstrap to polish the looks of the website. Notable parts are:
- Customized tab logo;
- Customized navbar;
- Customized backgrounds;
- **Customized apology() with personal image**;
- **Polished generate page with clean, dynamic Bootstrap classes (mobile friendly**);
- **Customized font using Google Font API**.


**ChatGPT API**

Firstly, we initialize the OpenAI API session by importing the *openai* library and providing the API key, this is stored in an *.env* file which called used *python-dotenv* in this fashion:
> *openai.api_key = os.getenv("OPENAI_API_KEY")*

We then want to generate the prompt:
- The input from the user is extracted with *request.form.get* and *request.form.getlist*;
- The input is validated, if thisi is not passed, it goes through the *apology()* function;
- The input is used to populated the *PROMPT*;
- The *PROMPT* is fed into OpenAI's API call;
- The API's output is cleaned up for display in HTML, then passed into the *output.html* page.

-------------------------------------------------------------------------------------------------------------------------------------------------

The results is a simple, but polished, website which provides a powerful tool and opens to future development of the idea.

**The website is also currently hosted at <https://cicero.riccardoscloud.com>**
*The hosted version doesn not currently include session functionalities, this might change in the future.*