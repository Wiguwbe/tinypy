from tinypy.runtime.testing import UnitTest

class StringUnitTests(UnitTest):
    def test_startswith(self):
        a = "012345"
        assert a.startswith("0")
        assert a.startswith("01")
        assert not a.startswith("1")

    def test_format(self):
        a = "{foo}{bar}d".format(dict(foo='abc', bar='123'))
        assert a == "abc123d"

    def test_percent(self):
        a = "{foo}d" % dict(foo='abc')
        assert a == "abcd"

    def test_find(self):
        a = "012345"
        assert a.find("0") == 0
        assert a.find("1") == 1

    def test_index(self):
        a = "012345"
        assert a.index("0") == 0

    def test_split(self):
        a = "012345"
        s = a.split('3')
        assert len(s) == 2
        assert s[0] == '012'
        assert s[1] == '45'

    def test_join(self):
        j = ' '.join(['abc', 'def'])
        assert j == 'abc def'


if __name__ == '__main__':
    tests = StringUnitTests()
    tests.run()

