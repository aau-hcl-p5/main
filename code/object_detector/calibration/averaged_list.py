class AveragedList:
    def __init__(self, size, gradient_size=5):
        self.size = size
        self.gradient_size = gradient_size
        self.back_list = [(0, 0)] * size
        self.index = 0

    def __getitem__(self, index):
        value, count = self.back_list[index]
        if count == 0:
            return 0
        return value / count

    def __setitem__(self, index, value):
        gradient_range = range(
            max(0, index - self.gradient_size),
            min(self.size, index + self.gradient_size)
        )
        for i in gradient_range:
            count = self.gradient_size - abs(index - i)
            self.back_list[i] = (self.back_list[i][0] + value * count, self.back_list[i][1] + count)

    def __iter__(self):
        return self

    def __next__(self):
        if self.index == len(self.back_list):
            self.index = 0
            raise StopIteration
        else:
            self.index += 1
            return self[self.index - 1]
