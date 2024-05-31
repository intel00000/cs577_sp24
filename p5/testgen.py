from random import randint, seed

# Setting a seed for reproducibility
seed(42)

# Number of instances
k = 200

# Generate test cases
test_cases = []
for _ in range(k):
    # Number of elements in each instance, ensuring a wide range of sizes
    j = randint(1, 100000)
    # Generating a list of random elements within the specified range
    elements = [randint(0, 2**31 - 1) for __ in range(j)]
    test_cases.append((j, elements))

# Generating the string representation of the test cases
test_case_str = f"{k}\n" + "\n".join(f"{j}\n" + " ".join(map(str, elements)) for j, elements in test_cases)

# Output the length of the generated test case string to check its size
file_name = "test_case.txt"
with open(file_name, 'w') as file:
    file.write(test_case_str)

file_name