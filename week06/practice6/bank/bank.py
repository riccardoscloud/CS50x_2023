greeting = input("Greeting: ")
firstword = greeting.split()[0].lower()
# print(f"{firstword}")

if "hello" in firstword:
    print("$0")
elif "h" == firstword[0]:
    print("$20")
else:
    print("$100")