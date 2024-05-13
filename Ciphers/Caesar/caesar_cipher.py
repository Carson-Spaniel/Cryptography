import string
alphabet = 'abcdefghijklmnopqrstuvwxyz'

def scoreText(data):    
    s = 0
    data = data.lower()
    common = "etaoin shrdlu"[::-1]
    
    for c in data:
        if c not in string.printable:
            return 0
        
        i = common.find(c)
        if i != -1:
            s += i
    
    return s

def caesarCipher(message, shift):
    message = message.lower()
    result = ""

    for letter in message:
        if letter in alphabet:
            index = alphabet.find(letter) 
            index = (index + shift)%(len(alphabet))

            if index < 0:
                index = index + len(alphabet)

            result = result + alphabet[index]

        else:
            result = result + letter

    return result

def caesarBreaker(cipherText):
    bestMessage = ''
    bestScore = -1e5
    for shift in range(len(alphabet)):
        message = ''
        for letter in cipherText:
            if letter in alphabet:
                index = alphabet.find(letter) 
                index = (index + shift)%(len(alphabet))

                if index < 0:
                    index = index + len(alphabet)

                message += alphabet[index]

            else:
                message += letter

        score = scoreText(message)

        if score > bestScore:
            bestScore = score
            bestMessage = message

    return bestMessage

        
plainText = "hello my name is carson." # Works better with longer plain texts
cipherText = caesarCipher(plainText,1)
foundPlainText = caesarBreaker(cipherText)

print(f'Plain text: {plainText}')
print(f'\nCipher text: {cipherText}')
print(f'\nFound plain text: {foundPlainText}')
