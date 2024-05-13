import base64
import string

letterFrequency = {
    'E': 12.70, 'T': 9.06, 'A': 8.17, 'O': 7.51, 'I': 6.97, 'N': 6.75,
    'S': 6.33, 'H': 6.09, 'R': 5.99, 'D': 4.25, 'L': 4.03, 'C': 2.78,
    'U': 2.76, 'M': 2.41, 'W': 2.36, 'F': 2.23, 'G': 2.02, 'Y': 1.97,
    'P': 1.93, 'B': 1.49, 'V': 0.98, 'K': 0.77, 'J': 0.15, 'X': 0.15,
    'Q': 0.10, 'Z': 0.07
}

def xorAscii(string, key):
    message = ''
    for i in range(0, len(string)):
        strChar = ord(string[i])
        keyChar = key
        message += chr(strChar ^ keyChar)
    return message

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

def getKeyLengths():
    return [length for length in range(2,41)]

def ascii_to_binary(s):
    return ''.join(format(ord(c), '08b') for c in s)

def calculate_hamming_distance(s1, s2):
    return sum(c1 != c2 for c1, c2 in zip(s1, s2))

def find_possible_key_length(ciphertext, lengths):
    key_len_candidate = None
    min_normalized = 1e6

    for key_length in lengths:
        total_hamming_distance = 0
        total_normalized_distance = 0

        num_blocks = len(ciphertext) // key_length
        for i in range(num_blocks - 1):
            block1 = ciphertext[i * key_length: (i + 1) * key_length]
            block2 = ciphertext[(i + 1) * key_length: (i + 2) * key_length]

            block_binary1 = ascii_to_binary(block1)
            block_binary2 = ascii_to_binary(block2)

            hamming_distance = calculate_hamming_distance(block_binary1, block_binary2)
            normalized_distance = hamming_distance / key_length

            total_hamming_distance += hamming_distance
            total_normalized_distance += normalized_distance

        average_normalized_distance = total_normalized_distance / (num_blocks - 1)

        if average_normalized_distance < min_normalized:
            key_len_candidate = key_length
            min_normalized = average_normalized_distance

    print("Found Possible Key length:", key_len_candidate, "\n")
    return key_len_candidate

ciphertext = ''
with open('file.txt', 'r') as file:
    print('Searching file...\n')
    for line in file:
        line = line.strip()
        ciphertext += line

ciphertext = base64.b64decode(ciphertext).decode('ascii')
lengths = getKeyLengths()
keyLenCandidate = find_possible_key_length(ciphertext, lengths)

blocks = [[] for _ in range(keyLenCandidate)]

for index in range(0,len(ciphertext),keyLenCandidate):
    block = ciphertext[index:index+keyLenCandidate]

    for i in range(len(block)):
        blocks[i].append(block[i])

key = ''
for i in range(len(blocks)):
    block = ''
    for j in range(len(blocks)):
        block += blocks[i][j]

    bestCharacter = '_'
    bestScore = 0
    bestMessage = ''
    for i in range(256):
        xorString = xorAscii(block, i)
        score = scoreText(xorString)

        if score > bestScore:
            bestScore = score
            bestCharacter = chr(i)
            bestMessage = xorString

    key += bestCharacter
    print(f'Character: {bestCharacter}')

# key = "Terminator X: Bring the noise"
print(f'Key: {key}')

decryptedMessage = ''
for i in range(len(ciphertext)):
    decryptedMessage += chr(ord(ciphertext[i]) ^ ord(key[i % len(key)]))

print(f'\nDecrypted Message: \n{decryptedMessage}')