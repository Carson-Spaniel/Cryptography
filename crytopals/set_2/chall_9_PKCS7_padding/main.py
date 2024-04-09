def pkcs_7(plaintext, blocksize):
    blocks = [plaintext[i:i+blocksize] for i in range(0, len(plaintext), blocksize)]
    last_block = blocks[-1]

    if len(last_block) < blocksize:
        pad = blocksize - len(last_block)
        blocks[-1] += bytes([pad] * pad)

    return b"".join(blocks)

plaintext = b"YELLOW SUBMARINE"

plaintext = pkcs_7(plaintext, 16)

print(f'New plaintext: {plaintext}')