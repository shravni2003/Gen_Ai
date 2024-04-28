#Write a python recursive function for prime number input limit in as parameter to
#it
def is_prime(n, i=2):
    """
    Check if a number is prime recursively.
    
    Args:
    - n: The number to check for primality.
    - i: The divisor to start checking from (default is 2).
    
    Returns:
    - True if the number is prime, False otherwise.
    """
    if n <= 2:
        return n == 2
    if n % i == 0:
        return False
    if i * i > n:
        return True
    return is_prime(n, i + 1)

def primes_within_limit(limit, current=2, primes=[]):
    """
    Find prime numbers within a given limit recursively.
    
    Args:
    - limit: The upper limit within which to find prime numbers.
    - current: The current number being checked for primality (default is 2).
    - primes: A list to store prime numbers (default is an empty list).
    
    Returns:
    - A list of prime numbers within the specified limit.
    """
    if current > limit:
        return primes
    if is_prime(current):
        primes.append(current)
    return primes_within_limit(limit, current + 1, primes)

# Example usage:
limit = int(input("Enter the limit: "))
prime_numbers = primes_within_limit(limit)
print("Prime numbers within the limit:", prime_numbers)


