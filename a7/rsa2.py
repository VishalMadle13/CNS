import random
import math

class RSA:
    def __init__(self, p, q):
        """Generates a public and private keypair for the RSA cryptosystem."""
        self.n = p * q
        self.phi = (p - 1) * (q - 1)
        self.e = random.randint(2, self.phi - 1)
        while math.gcd(self.e, self.phi) != 1:
            self.e = random.randint(2, self.phi - 1)

        self.d = 1
        for i in range(2, self.phi + 1):
            if (self.e * i) % self.phi == 1:
                self.d = i
                break

        self.public_key = (self.n, self.e)
        self.private_key = (self.n, self.d)

    def encrypt(self, message):
        """Encrypts the given message using the RSA cryptosystem."""
        encrypted_message = []
        for letter in message:
            encrypted_message.append(pow(ord(letter), self.public_key[1], self.public_key[0]))
        return encrypted_message

    def decrypt(self, encrypted_message):
        """Decrypts the given encrypted message using the RSA cryptosystem."""
        decrypted_message = []
        for encrypted_letter in encrypted_message:
            decrypted_message.append(chr(pow(encrypted_letter, self.private_key[1], self.private_key[0])))
        return ''.join(decrypted_message)

# Example usage:

p = int(input("Enter a prime number p: "))
q = int(input("Enter a prime number q: "))

rsa = RSA(p, q)

message = 'Hello, world!'

print('Public key:', rsa.public_key)
print('Private key:', rsa.private_key)
print('n:', rsa.n)
print('e:', rsa.e)
print('d:', rsa.d)

encrypted_message = rsa.encrypt(message)

decrypted_message = rsa.decrypt(encrypted_message)

print('Original message:', message)
print('Encrypted message:', encrypted_message)
print('Decrypted message:', decrypted_message)



''''
Select 2 largest prime numbers p annd q
Calculate 
    n = p*q   
    phi = (p-1)*(q-1) 
    
    [
        e = random(2,phi-1) 
        1 < e < phi
        gcd(phi , e) == 1
    ]

calculate 
    d = e^(-1)mod(phi)
    ed = 1mod(phi)

public key  = { e, n}
private key = { d, n}   

Encryption C = M^(e)MOD(n)
Decryption M = C^(d)MOD(n)


'''
# Example 
''''
p = 3
q = 11
n = p*q = 33
phi = (p - 1) * (q - 1) = 20
so let,
    e = 7 as 1< e=7 <phi and gcd(7,20) == 1
Now,
de = 1MOD(phi)
d*7 = 1MOD(20)
So,
d = 3
Public Key : {7, 33}, 
Private Key : {3, 33}

Message to be Encrypted is "Hello"
C = H^7 mod 33 = 5498
After Decrypting we get the Message back.
M = C^3 mod 33 = 5498 ^ 3 mod 33 = Hello



'''