with open("Doomsday00.wav", "rb") as f:
    data = f.read()

# Header 
print("HEADER:")
print(data[:44])

# passe bytes audio header
print("\nAUDIO SAMPLE:")
print(list(data[44:100]))
