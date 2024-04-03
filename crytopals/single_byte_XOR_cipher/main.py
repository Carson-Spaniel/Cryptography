letterFrequency = {
    'E': 12.70, 'T': 9.06, 'A': 8.17, 'O': 7.51, 'I': 6.97, 'N': 6.75,
    'S': 6.33, 'H': 6.09, 'R': 5.99, 'D': 4.25, 'L': 4.03, 'C': 2.78,
    'U': 2.76, 'M': 2.41, 'W': 2.36, 'F': 2.23, 'G': 2.02, 'Y': 1.97,
    'P': 1.93, 'B': 1.49, 'V': 0.98, 'K': 0.77, 'J': 0.15, 'X': 0.15,
    'Q': 0.10, 'Z': 0.07
}

def xorAscii(hex_string, key):
    message = b''
    for i in range(0, len(hex_string), 2):
        hexByte = hex_string[i:i + 2]
        hexVal = int(hexByte, 16)
        message += bytes([key ^ hexVal])
    return message.decode('ascii', errors='ignore')

def scoreText(s):
    observedFreq = {}
    for letter in s:
        if letter.isalpha():
            if letter.upper() in observedFreq:
                observedFreq[letter.upper()] += 1
            else:
                observedFreq[letter.upper()] = 1

    score = 0.0
    for key in letterFrequency:
        letter = key
        expectedFreq = letterFrequency[key]
        observedFreqLetter = observedFreq.get(letter.upper(), 0)
        chi = pow(observedFreqLetter - expectedFreq, 2) / expectedFreq
        score += chi

    return score

encoded = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
bestCharacter = ''
bestScore = 1e5
bestMessage = ''
for i in range(256):
    xorString = xorAscii(encoded, i)
    score = scoreText(xorString)

    if score < bestScore:
        bestScore = score
        bestCharacter = chr(i)
        bestMessage = xorString

print(f'Found character: {bestCharacter}')
print(f'Message reads: {bestMessage}')