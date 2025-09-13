# 📖 English–Chinese Dictionary (Terminal)

A lightweight terminal-based English–Chinese dictionary powered by API.  
Supports **bidirectional translation**:  
- **English → Chinese**  
- **Chinese → English**  

---

## 🚀 Features
- Translate English words into Chinese
- Translate Chinese words into English
- Runs entirely in the terminal
- View and manage history / favorites
- Lightweight dependencies

---

## 🛠 Dependencies

This project requires the following:

- `gcc` (C compiler)
- `make`
- `curl` (`libcurl4-openssl-dev`)
- `openssl` (`libssl-dev`)
- `uuid` (`uuid-dev`)
- `ncurses` (`libncurses5-dev`, `libncursesw5-dev`)

On Ubuntu/WSL, install them with:

```bash
sudo apt update
sudo apt install build-essential \
                 libcurl4-openssl-dev \
                 libssl-dev \
                 uuid-dev \
                 libncurses5-dev \
                 libncursesw5-dev
```
---

## 📅 Status (as of 2025-09-13)

- [X] Basic operations ready
- [X] Search functionality for English/Chinese words
- [X] Terminal UI via ncurses
- [X] Makefile for easy compilation

## 📋 To-Do (Planned Features)

- [X] Search for English or Chinese words
- [X] UI via ncurses
- [ ] Error animations
- [X] Expand menu and features
- [ ] Handle long words (>20 symbols) or words with spaces
- [X] Parse API response cleanly (via cJSON)
- [X] Create Makefile
- [X] Organize folder structure

## 💾 Installation

Clone the repository and compile using the provided Makefile:

# Clone repo
```
git clone https://github.com/snikmas/encn-dict-terminal.git
cd encn-dict-terminal

# Compile
make

# Run the program
./bin/main

```
## 📖 Usage

1. Launch the program:
```
./bin/main
```

2. Navigate the menu:

- Translate CN→EN or EN→CN
- View saved words
- View translation history
= Exit

3. Use on-screen prompts to input words, save translations, or manage history.
