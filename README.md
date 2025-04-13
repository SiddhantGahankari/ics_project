# Translation Model

This project implements a simple natural language translation system using pre-trained word embeddings. It supports basic English-to-French and English-to-Spanish word and sentence translation by leveraging cosine similarity between word vectors.

## 📁 Project Structure

ics_project/# Header files 
├── include/ <br>
 ├── common.h  <br>
 ├── eval.h  <br>
 ├── globals.h <br>
 ├── io.h  <br>
 ├── translate.h<br> 
 │── vector.h <br>
├── src/ # Source files <br>
  ├── *_eval.c <br>
  ├── *_globals.c <br>
  ├── *_io.c <br>
  ├── *_main.c  <br>
  ├── *_translate.c <br>
  │── *_vector.c <br>
├── obj/ # Object files <br>
├── makefile # Build instructions <br>
├── main # Compiled binary (after build) <br>
├── .gitignore <br>
|── LICENSE<br>



## Features included in the project:

- Load and process word embeddings from files
- Translate individual words using top-k cosine similarity
- Translate entire sentences word-by-word
- Evaluate similarity and semantic closeness of translations
- Modular code architecture with clear separation of concerns

## Build Instructions

```bash
make
