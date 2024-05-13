def pkcs_7(plaintext, blocksize):
    blocks = [plaintext[i:i+blocksize] for i in range(0, len(plaintext), blocksize)]
    last_block = blocks[-1]

    if len(last_block) < blocksize:
        pad = blocksize - len(last_block)
        blocks[-1] += bytes([pad] * pad)

    return b"".join(blocks)

def unpkcs_7(padded_text):
    pad_byte = padded_text[-1]
    if pad_byte < 1 or pad_byte > 16:
        raise ValueError("Invalid padding byte")

    padding = padded_text[-pad_byte:]
    if not all(padding[b] == pad_byte for b in range(len(padding))):
        raise ValueError("Invalid padding bytes")

    return padded_text[:-pad_byte]

# Assuming you have already padded the plaintext
padded_plaintext = pkcs_7(b"YELLOW SUBMARINE", 20)

print(f"Padded plaintext: {padded_plaintext}")

unpadded_plaintext = unpkcs_7(padded_plaintext)
print(f"Unpadded plaintext: {unpadded_plaintext}")