# Check dependencies
## Check python installed

Check python3 and sqlite3 package installed
 
```bash
python --version
pip check sqlite3
``` 
if sqlite3 is not installed run

```bash
pip install sqlite3
```

## Run database generator

```bash
cd automation
python ./generate_db.py
```