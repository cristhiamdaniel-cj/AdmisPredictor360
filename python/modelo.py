import os
import struct
import json
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.model_selection import train_test_split

# --- Función para leer el archivo binario ---
def read_binary_file(filename):
    rows = []
    with open(filename, 'rb') as f:
        # Suponemos size_t de 8 bytes (formato "Q")
        num_rows = struct.unpack("Q", f.read(8))[0]
        for _ in range(num_rows):
            num_cols = struct.unpack("Q", f.read(8))[0]
            row = []
            for _ in range(num_cols):
                length = struct.unpack("Q", f.read(8))[0]
                cell = f.read(length).decode('utf-8')
                row.append(cell)
            rows.append(row)
    return rows

# --- Lectura del archivo binario y construcción del DataFrame ---
data = read_binary_file("Admission_Predict.bin")
df = pd.DataFrame(data[1:], columns=data[0])
# Limpiar espacios en blanco en los nombres de columnas
df.columns = df.columns.str.strip()

# Convertir columnas a numéricas si es posible
for col in df.columns:
    try:
        df[col] = pd.to_numeric(df[col])
    except Exception:
        pass

# --- Construcción del modelo ---
features = ['GRE Score', 'TOEFL Score', 'University Rating', 'SOP', 'LOR', 'CGPA', 'Research']
X = df[features]
y = df['Chance of Admit']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

# --- Creación de imágenes en la carpeta "images" ---
if not os.path.exists("images"):
    os.makedirs("images")

# Matriz de correlación
corr_matrix = df.corr()
plt.figure(figsize=(10, 8))
sns.heatmap(corr_matrix, annot=True, fmt=".2f", cmap="coolwarm")
plt.title("Matriz de Correlación")
plt.savefig("images/correlation_matrix.png")
plt.close()

# Gráfica de errores (residuals)
residuals = y_test - y_pred
plt.figure(figsize=(8,6))
plt.scatter(y_pred, residuals)
plt.axhline(0, color='red', linestyle='--')
plt.xlabel("Predicciones")
plt.ylabel("Errores (Residuals)")
plt.title("Distribución de Errores")
plt.savefig("images/residuals.png")
plt.close()

# --- Exportación de los parámetros del modelo a un archivo JSON ---
model_params = {
    "intercept": model.intercept_,
    "coefficients": {feature: coef for feature, coef in zip(features, model.coef_)},
    "mse": mse,
    "r2": r2
}

with open("model.json", "w") as json_file:
    json.dump(model_params, json_file, indent=4)

print("Modelo construido y exportado en 'model.json'.")
print("Imágenes guardadas en la carpeta '/images'.")

