class ModelConfig:
    def __init__(self, input_size, hidden_size, output_size, learning_rate):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size
        self.learning_rate = learning_rate

    @property
    def input_size(self):
        return self._input_size

    @input_size.setter
    def input_size(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("input_size必须为正整数")
        self._input_size = value

    @property
    def hidden_size(self):
        return self._hidden_size

    @hidden_size.setter
    def hidden_size(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("hidden_size必须为正整数")
        self._hidden_size = value

    @property
    def output_size(self):
        return self._output_size

    @output_size.setter
    def output_size(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("output_size必须为正整数")
        self._output_size = value

    @property
    def learning_rate(self):
        return self._learning_rate

    @learning_rate.setter
    def learning_rate(self, value):
        if not isinstance(value, (int, float)) or value <= 0 or value > 1:
            raise ValueError("learning_rate必须在(0, 1]之间")
        self._learning_rate = value

if __name__ == "__main__":
    config = ModelConfig(128, 64, 10, 0.01)

    try:
        config.input_size = -5
    except ValueError as e:
        print(f"设置非法值被拦截: {e}")

    try:
        config.learning_rate = 1.5
    except ValueError as e:
        print(f"设置非法值被拦截: {e}")