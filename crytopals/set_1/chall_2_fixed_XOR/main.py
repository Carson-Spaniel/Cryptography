input_hex = "1c0111001f010100061a024b53535009181c"
xor_hex = "686974207468652062756c6c277320657965"

result = ''
for i in range(len(input_hex)):
    input_int = int(input_hex[i], 16)
    xor_int = int(xor_hex[i], 16)

    xor_result = input_int ^ xor_int
    result += format(xor_result, 'x')

print(result)
