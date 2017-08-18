
import pytest


def pytest_addoption(parser):
    parser.addoption("--cmdopt", action="store", default="4040",
                     help="port: 4040 default")


@pytest.fixture
def cmdopt(request):
    return request.config.getoption("--cmdopt")
