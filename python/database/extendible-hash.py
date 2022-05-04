PAGE_SZ = 10


class Page:
    def __init__(self) -> None:
        """
        the page depth and the list/map to store k/v
        """
        self.local_depth = 0
        self.map = []

    def full(self) -> bool:
        """
        check the page_size >= PAGE_SZ
        """
        return len(self.map) >= PAGE_SZ

    def put(self, k, v) -> None:
        """
        don't allow two same k exsist
        """
        for i, (key, value) in enumerate(self.map):
            if k == key:
                del self.map[i]
                break
        self.map.append((k, v))

    def get(self, k):
        for (key, value) in self.map:
            if k == key:
                return value
        return None

    def get_local_high_bit(self):
        return 1 << self.local_depth


class ExtendibleHashing:
    def __init__(self) -> None:
        self.global_path = 0
        self.directory = [Page()]

    def get_page(self, k):
        h = hash(k)
        return self.directory[h & ((1 << self.global_path) - 1)]

    def put(self, k, v) -> None:
        p = self.get_page(k)
        full = p.full()
        p.put(k, v)
        if full:
            if p.local_depth == self.global_path:
                self.global_path += 1
                self.directory *= 2
            p0 = Page()
            p1 = Page()
            p0.local_depth = p1.local_depth = p.local_depth + 1
            high_bit = p.get_local_high_bit()
            for k2, v2 in p.map:  # re-hashing
                h = hash(k2)
                new_p = p1 if (h & high_bit) else p0
                new_p.put(k2, v2)
            for i in range(hash(k) & (high_bit - 1), len(self.directory), high_bit):
                self.directory[i] = p1 if (i & high_bit) else p0

    def get(self, k):
        return self.get_page(k).get(k)


if __name__ == "__main__":
    eh = ExtendibleHashing()
    N = 10088
    l = list(range(N))

    import random

    random.shuffle(l)
    for x in l:
        eh.put(x, x)
    print(l)

    for i in range(N):
        print(eh.get(i))
