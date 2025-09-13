# 📖 English–Chinese Dictionary (Terminal)

A lightweight terminal-based English–Chinese dictionary powered by API.  
Supports **bidirectional translation**:  
- **English → Chinese**  
- **Chinese → English**  

---

## 🚀 Features
- Search English words for Chinese translations
- Search Chinese words for English translations
- Runs entirely in the terminal
- Check history / favorites
- Lightweight dependencies

---

## 🛠 Dependencies
- `curl` – for sending HTTP requests  
- `openssl` – for secure requests (e.g., API signing)  
- `uuid` – for generating unique request IDs  

---

## 📅 Status (as of 2025-09-13)
✅ Basic operations ready
✅ Search functionality for English/Chinese words
✅ Terminal UI via ncurses
✅ Makefile for easy compilation

---

## 📋 To-Do (Requirements)
- [x] Search for English or Chinese words  
- [X] UI via **ncurses**  
- [ ] Error animations  
- [ ] Expand menu and features  
- [ ] Handle words >20 symbols or containing spaces  
- [X] Parse HTML response cleanly  
- [x] Create `Makefile`  
- [x] Organize folder structure  

---

## Instalation

Clone the repository and compile using Makefile
```
# Clone repo
git clone https://github.com/snikmas/encn-dict-terminal.git

# Enter project folder
cd encn-dict-terminal

# Compile
make

# Run the program
bin/main
```

### Requirements: 
- Linux or WSL environment
- C compiler (gcc)
- Dependencies: curl, openssl, uuid, ncurses, cJSON


