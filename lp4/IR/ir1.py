from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

# Function to read file content
def read_file(file_path):
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            return f.read()
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return ""

# Function to compute similarity between two documents
def compute_similarity(doc1, doc2):
    documents = [doc1, doc2]
    vectorizer = TfidfVectorizer()
    tfidf_matrix = vectorizer.fit_transform(documents)
    similarity = cosine_similarity(tfidf_matrix[0:1], tfidf_matrix[1:2])
    return similarity[0][0]

# Paths to your files
file1 = "file1.txt"
file2 = "file2.txt"

# Read content from files
doc1 = read_file(file1)
doc2 = read_file(file2)

# Compute similarity
similarity_score = compute_similarity(doc1, doc2)
print(f"Similarity score between documents: {similarity_score:.4f}")
