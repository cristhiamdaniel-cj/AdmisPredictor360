import json

def export_model_to_json(model, features, mse, r2, output_path="model.json"):
    """
    Exporta los parámetros del modelo a un archivo JSON, redondeando los valores
    a 3 dígitos decimales, y muestra en consola la ecuación lineal.
    """
    model_params = {
        "intercept": round(model.intercept_, 3),
        "coefficients": {feature: round(coef, 3) for feature, coef in zip(features, model.coef_)},
        "mse": round(mse, 3),
        "r2": round(r2, 3)
    }
    with open(output_path, "w") as f:
        json.dump(model_params, f, indent=4)
    equation = f"Chance of Admit = {round(model.intercept_, 3)}"
    for feature, coef in zip(features, model.coef_):
        equation += f" + ({round(coef, 3)} * {feature})"
    print("Ecuación del modelo:")
    print(equation)
