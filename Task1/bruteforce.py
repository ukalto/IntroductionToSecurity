import hashlib
import random
import string

while 1:
    pw = ''.join(random.choice(string.ascii_lowercase) for x in range(19))
    # 0x61, 0x73, 0x39, 0x62, 0x32, 0x33, 0x42, 0x45
    salt = "as9b23BE"
    hash_ = hashlib.sha1(salt.encode() + pw.encode()).hexdigest()
    # 0x00 0xc7 0x91
    if hash_[39] == '1' and hash_[38] == '9' and hash_[37] == '7' and hash_[36] == 'c' and hash_[35] == '0' and hash_[34] == '0':
        print(pw)
        print(hash_)
        break

salt_hex = ""
pw_hex = ""
for i in range(len(salt)):
    salt_hex += salt[i].encode('utf-8').hex()
for i in range(len(pw)):
    pw_hex += pw[i].encode('utf-8').hex()
pw_with_hash = pw_hex + "00" + salt_hex + hash_
final = ""
for i in range(0, int(len(pw_with_hash)), 2):
    final = "{0}\\x{1}{2}".format(final, pw_with_hash[i], pw_with_hash[i + 1])
print(final)
