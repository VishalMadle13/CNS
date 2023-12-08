def playfair_cipher(plaintext, key):  
    alphabet = 'abcdefghiklmnopqrstuvwxyz'  
    key = key.lower().replace(' ', '').replace('j', 'i')  
    key_square = ''  
    for letter in key + alphabet:  
        if letter not in key_square:  
            key_square += letter  
    plaintext = plaintext.lower().replace(' ', '').replace('j', 'i')  
    if len(plaintext) % 2 == 1:  
        plaintext += 'x'  

    digraphs = [plaintext[i:i+2] for i in range(0, len(plaintext), 2)]  

    digraph1 = []

    for digraph in digraphs:
        if digraph[0] == digraph[1] :
            digraph = digraph[0] + "x"
        digraph1.append(digraph)

    return digraph1, key_square

def encrypt(digraph, key_square):  
    a, b = digraph  
    row_a, col_a = divmod(key_square.index(a), 5)  # divmod => quotient, remainder
    row_b, col_b = divmod(key_square.index(b), 5)  
    if row_a == row_b:  
        col_a = (col_a + 1) % 5  
        col_b = (col_b + 1) % 5  
    elif col_a == col_b:  
        row_a = (row_a + 1) % 5  
        row_b = (row_b + 1) % 5  
    else:  
        col_a, col_b = col_b, col_a  
    
    return key_square[row_a*5+col_a] + key_square[row_b*5+col_b]  

def decrypt(digraph, key_square):  
    a, b = digraph 
       
    row_a, col_a = divmod(key_square.index(a), 5)  
    row_b, col_b = divmod(key_square.index(b), 5)  
    if row_a == row_b:  
        col_a = (col_a - 1) % 5  
        col_b = (col_b - 1) % 5  
    elif col_a == col_b:  
        row_a = (row_a - 1) % 5  
        row_b = (row_b - 1) % 5  
    else:  
        col_a, col_b = col_b, col_a  
        
    return key_square[row_a*5+col_a] + key_square[row_b*5+col_b]  

def userinput():
    keyinp = input("Enter the key: ")
    datainp = input("Enter the data")
    return keyinp,datainp


key, message = userinput()
choice = int(input("Choose 0 for encryption or Choose 1 for decryption "))
  
# message = 'atttack'  
# key = 'monarchy'   

digraphs, key_square = playfair_cipher(message, key)

if choice == 0 :
    ciphertext = ""  
    for digraph in digraphs:  
        ciphertext += encrypt(digraph, key_square)  

    print(ciphertext)

else :
    decrypted_text = "" 

    for digraph in digraphs:  
        val = decrypt(digraph, key_square)

        new_val = ""

        if val[1] == 'x' :
            new_val = val[0] + val[0]
        else :
            new_val = val

        decrypted_text += new_val  

    print(decrypted_text)