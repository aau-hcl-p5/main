#F.L.A.T: Object recognition
This python project consists of the object recognition part of the F.L.A.T system
It is build on python3.6, utilizing tensorflow for machine intelligence parts

## Usage
To run it, make sure you have a virtual environment 
(it helps not-clog your dependencies.. but it's optional. Google it)

When the venv is activated (or not.. i dont care) run:

`pip3 install -r requirements.txt`

run (all commands in this document should be run with this dir as working directory)

```python main.py```


Optional flag of "-a" can specify what algorithm. by default, it is "goturn".



## Development
it is recommended to create en venv for working with this.

Please use pylint for linting
Issues with pylint, however, is that it doesn't (yet) understand typing,
nor check the content of docstrings, 
so remember to check that content of docstrings actually follow the signature
of the given method. (args, etc)
In addition, all public methods **MUST** utilize typing.

####To run all tests either:
 - Use pycharm (it has coverage and testing)
 - run `python3 -m unittest`

####to run linter:

Run `pylint`

####To check coverage: 

run `coverage run -m unittest && coverage report`

(alternatively to get a pretty html report: `coverage run -m unittest && coverage html` )
