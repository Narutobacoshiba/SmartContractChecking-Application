#Back-end

## Create Database
```
Before running the script, you must initialize a database named solidityTocpn.

  - cd script
  - python3 createDatabase.py 
```

# Update Tools
```
Copy unfolding tools (just the executable with the name 'unfolding') to the back-end/tools/tools directory
```

## Run project
```
Makemigrations
  - python3 manage.py makemigrations
  - python3 manage.py migrate
 
Run
  - python3 manage.py runserver 8000
```