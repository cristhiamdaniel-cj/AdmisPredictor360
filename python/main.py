import struct
import pandas as pd
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.linear_model import LinearRegression
import json

bin_file = 'data/Admission_Predict_new.bin'

# Estructura del registro: 4 enteros + 3 doubles + 1 entero + 1 double
record_format = '<iiii dd d i d'  # < = little endian, sin padding
record_size = struct.calcsize(record_format)

with open(bin_file, 'rb') as f:
    # Leer cantidad de registros (primeros 8 bytes si es size_t o 4 si es uint32)
    count_bytes = f.read(8)
    total_records = struct.unpack('<Q', count_bytes)[0]  # Usa <I si fuera uint32
    print(f"Registros esperados: {total_records}")

    records = []
    for i in range(total_records):
        bytes_read = f.read(record_size)
        if len(bytes_read) != record_size:
            print(f"Registro incompleto en posición {i}. Se omite.")
            continue
        record = struct.unpack(record_format, bytes_read)
        records.append(record)

# Crear DataFrame
columns = [
    "Serial No.", "GRE Score", "TOEFL Score", "University Rating",
    "SOP", "LOR", "CGPA", "Research", "Chance of Admit"
]
df = pd.DataFrame(records, columns=columns)
print(df.info())
print(df.head())


# 1. Eliminar la columna Serial No.
df = df.drop(columns=["Serial No."])

# 2. Visualizar matriz de correlación
plt.figure(figsize=(10, 8))
sns.heatmap(df.corr(), annot=True, cmap="coolwarm", fmt=".2f")
plt.title("Matriz de Correlación")
plt.tight_layout()
plt.savefig("images/heatmap_correlacion.png")
plt.show()

# 3. Graficar dispersión (scatter plots) respecto a la variable dependiente
target = "Chance of Admit"
features = [col for col in df.columns if col != target]

plt.figure(figsize=(14, 10))
for i, col in enumerate(features, 1):
    plt.subplot(3, 3, i)
    sns.scatterplot(x=df[col], y=df[target])
    plt.axhline(y=df[target].mean(), color='red', linestyle='--', label='Media')
    plt.title(f'{col} vs {target}')
    plt.xlabel(col)
    plt.ylabel(target)
    plt.legend()

plt.tight_layout()
plt.savefig("images/scatter_plots.png")
plt.show()

# 4. Entrenar modelo de regresión lineal
X = df[features]
y = df[target]

model = LinearRegression()
model.fit(X, y)

# 5. Guardar coeficientes y el intercepto en archivo JSON
coef_dict = {feature: coef for feature, coef in zip(features, model.coef_)}
coef_dict["intercept"] = model.intercept_

with open("data/modelo_coeficientes.json", "w") as f:
    json.dump(coef_dict, f, indent=4)

print("Modelo entrenado y coeficientes guardados en 'output/modelo_coeficientes.json'")
