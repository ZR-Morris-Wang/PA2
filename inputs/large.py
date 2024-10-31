n = 85000
filename = "170000.in"

with open(filename, "w") as f:
    # Write the number of endpoints
    f.write(f"{2 * n}\n")
    
    # Write each chord in the form "i i+n"
    for i in range(n):
        f.write(f"{i} {i + n}\n")
    
    # End the input with a single "0"
    f.write("0\n")
