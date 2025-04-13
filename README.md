# Translation Model

This project implements a simple natural language translation system using pre-trained word embeddings. It supports basic English-to-French and English-to-Spanish word and sentence translation by leveraging cosine similarity between word vectors.

## 📁 Project Structure

ics_project/# Header files 
├── include/ 
 ├── common.h │ 
 ├── eval.h │ 
 ├── globals.h 
 ├── io.h │ 
 ├── translate.h 
 │── vector.h 
├── src/ # Source files 
  ├── *_eval.c 
  ├── *_globals.c 
  ├── *_io.c 
  ├── *_main.c  
  ├── *_translate.c 
  │── *_vector.c
├── obj/ # Object files 
├── makefile # Build instructions 
├── main # Compiled binary (after build) 
├── .gitignore 
|── LICENSE



## Features included in the project:

- Load and process word embeddings from files
- Translate individual words using top-k cosine similarity
- Translate entire sentences word-by-word
- Evaluate similarity and semantic closeness of translations
- Modular code architecture with clear separation of concerns

## Build Instructions

```bash
make
