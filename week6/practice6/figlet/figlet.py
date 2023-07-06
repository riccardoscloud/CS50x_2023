import sys
import random
from pyfiglet import Figlet

figlet = Figlet()

# Accept only either 0 or 2 command-line arguments
if len(sys.argv) != 1 and len(sys.argv) != 3:
    print("Use 0 command-line arguments for a random font, 2 for a specific font.")
    sys.exit(1)

# Initialize the font list
font_list = figlet.getFonts()

# If no font is specified, pick a random one
if len(sys.argv) == 1:
    random_font = font_list[random.randrange(len(font_list))]
    figlet.setFont(font=random_font)

# If user tries to specify a font
if len(sys.argv) == 3:
    # Make sure format is correct
    if ((sys.argv[1] != "-f") and (sys.argv[1] != "--font")) or (sys.argv[2] not in font_list):
        print("Use -f or --font as the first argument, then the font name as the second")
        sys.exit(1)
    # If it is, set the font
    else:
        figlet.setFont(font=sys.argv[2])

# Get user text input
text = input("Input text: ")

# Print result
print(figlet.renderText(text))