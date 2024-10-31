import random

def generate_random_pairs(n):
    if n % 2 != 0:
        raise ValueError("n must be even.")
    
    numbers = list(range(n))
    random.shuffle(numbers)
    
    pairs = [(numbers[i], numbers[i+1]) for i in range(0, n, 2)]
    filename = f"{n}.in"
    
    with open(filename, "w") as file:
        file.write(f"{n}\n")  # Write n at the beginning
        for x, y in pairs:
            file.write(f"{x} {y}\n")
        file.write("0\n")  # Write 0 at the end

n = 20000  # Example with n=10
generate_random_pairs(n)
