import datetime
from typing import List

from calibration.utils import Package


# noinspection PyArgumentList
def save_packages(packages: List[Package]):
    file = open(datetime.datetime.now().strftime('%m_%d_%H_%M_%S.result'), 'w')
    file.write("\n".join(str(p) for p in packages))
