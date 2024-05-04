import string
alphabet = 'abcdefghijklmnopqrstuvwxyz'

letterFrequency = {
    'E': 12.70, 'T': 9.06, 'A': 8.17, 'O': 7.51, 'I': 6.97, 'N': 6.75,
    'S': 6.33, 'H': 6.09, 'R': 5.99, 'D': 4.25, 'L': 4.03, 'C': 2.78,
    'U': 2.76, 'M': 2.41, 'W': 2.36, 'F': 2.23, 'G': 2.02, 'Y': 1.97,
    'P': 1.93, 'B': 1.49, 'V': 0.98, 'K': 0.77, 'J': 0.15, 'X': 0.15,
    'Q': 0.10, 'Z': 0.07
}

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
