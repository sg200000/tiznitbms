---
project_name: tiznitbms
---

# {{ page.project_name }}
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

# Build and install software

To build and install software run the following command

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/custom/installation/directory ..
cmake --build .
cmake --install .
```