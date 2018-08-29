import os

path = os.path.dirname(os.path.abspath(__file__))
__all__ = [
    name for name in os.listdir(path) if os.path.isdir('{0}/{1}'.format(path, name))
    if 'python' in os.listdir('{0}/{1}'.format(path, name))
]
