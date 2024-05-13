import requests
from api_key import url, querystring, headers

def fill_guessed(guessed, quote, character):
    for i in range(len(quote)):
        if quote[i].upper() == character:
            guessed[i] = character
    return guessed

def play_game(quote, author, category):
    guessed = []
    for i in quote:
        if i.isalpha():
            guessed.append('_')
        else:
            guessed.append(i)
    print("Welcome to the XOR Cipher Game!")
    print("Can you guess the original quote?")
    
    previousChar = ''
    incorrect = 0
    characterAttempted = []
    correctCharacters = []
    while True:
        print(f'\nHint: {category.title()}')
        print("Current Quote:\n")
        for char in guessed:
            if char == " ":
                print('  ', end='')
            elif char == previousChar:
                print(f'\033[32m{char}\033[0m', end='')
            else:
                print(char, end='')
        print('\n')
        print(f"Incorrect characters:\n{characterAttempted}\n")
        print(f"Correct characters:\n{correctCharacters}\n")

        character = input("Enter a single letter guess (or 'exit' to quit): ").upper()
        
        if character == 'EXIT':
            print("Quitting game...\n")
            break
        
        if len(character) != 1 or not character.isalpha():
            print("Invalid input. Please enter a single letter.")
            previousChar = ''
            continue
        
        if character in guessed:
            print("You've already guessed this character. Try a different one.")
            incorrect +=1
            previousChar = ''
            continue
        
        found = False
        for i in range(len(quote)):
            if quote[i].upper() == character:
                guessed[i] = character
                found = True
                previousChar = character
        if found:
            print("Correct!")
            print('\n----------------------------------------------------')
            correctCharacters.append(character)
        else:
            print("Incorrect guess.")
            print('\n----------------------------------------------------')
            previousChar = ''
            incorrect +=1
            characterAttempted.append(character)
        if "_" not in guessed:
            print("\nCongratulations! You've guessed the entire quote!")
            print("Here's the original quote:")
            print(f'\n"{quote}" - {author}\n')
            print(f"You had {incorrect} incorrect guesses.")
            break

# response = [{'id': 1716, 'text': 'I was born to be alone, and I always shall be but now I want to be.', 'author': 'Mary MacLane', 'category': 'alone'}]

# quote = response[0]["text"]
# author = response[0]["author"]
# category = response[0]["category"]

response = requests.get(url, headers=headers, params=querystring)

if response:
    quote = response.json()[0]["text"]
    author = response.json()[0]["author"]
    category = response.json()[0]["category"]

play_game(quote, author, category)
