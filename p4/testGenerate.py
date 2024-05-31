import random

def generate_test_case(cache_size, num_requests, max_page_number):
    requests = []
    for _ in range(num_requests):
        # Mix of sequential and random requests
        if random.random() < 0.5:
            # Sequential block to potentially fill the cache
            requests.append(random.randint(1, max_page_number // 2))
        else:
            # Random access to challenge the cache logic
            requests.append(random.randint(1, max_page_number))

    return (cache_size, num_requests, requests)

cache_size = 100000
num_requests = 100000
max_page_number = 100000 # Adjust based on the desired range of page numbers
numInstances = 20

print(numInstances)
for i in range(numInstances):
    test_case = generate_test_case(random.randint(1, cache_size), random.randint(1, num_requests), random.randint(1, max_page_number))
    print(test_case[0])
    print(test_case[1])
    print(" ".join(str(x) for x in test_case[2]))