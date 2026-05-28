with open("Doomsday00.wav", "rb") as f:
    data = f.read()

# Header (44 premiers bytes)
print("HEADER:")
print(data[:44])

# quelques bytes audio après header
print("\nAUDIO SAMPLE:")
print(list(data[44:100]))