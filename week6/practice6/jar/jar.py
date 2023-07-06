class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Invalid input")
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        string = "🍪" * self.size
        return string

    def deposit(self, n):
        self._size += n
        if self.size > self.capacity:
            raise ValueError("Jar is full!")

    def withdraw(self, n):
        self._size -= n
        if self.size < 0:
            raise ValueError("Jar is empty!")

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
    jar = Jar()

    print(str(jar.capacity))
    print(str(jar))

    jar.deposit(9)
    print(str(jar))

    jar.withdraw(1)
    print(str(jar))

main()
