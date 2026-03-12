import string

symbols = (
    string.ascii_lowercase +   # a-z
    string.ascii_uppercase +   # A-Z
    string.digits +            # 0-9
    string.punctuation +       # !@#$%^&*()_+{}[]...
    " "                        # пробел
)

dict_spels = {ch: i for i, ch in enumerate(symbols)}

title = "ahello world"


for ttl in title:
    print(dict_spels[ttl], end=" ")
    
print("\n", len(dict_spels))