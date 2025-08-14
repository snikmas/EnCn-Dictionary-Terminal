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
- `regex` – (optional) for parsing HTML responses  

---

## 📅 Status (as of 2025-08-14)
✅ Menu navigation implemented  
✅ Can get words and translate  
🔄 More UI features coming soon  

---

## 📋 To-Do (Requirements)
- [x] Search for English or Chinese words  
- [ ] UI via **ncurses**  
- [ ] Error animations  
- [ ] Expand menu and features  
- [ ] Handle words >20 symbols or containing spaces  
- [ ] Parse HTML response cleanly  
- [ ] Create `Makefile`  
- [ ] Organize folder structure  

---

## 🧪 To-Do (Tests)
- [ ] Write automated tests  
- [ ] Test special cases (e.g., punctuation, slang, traditional vs simplified)  
- [ ] Define behavior when **no internet connection** is detected  

---
