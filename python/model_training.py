import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

def train_model_sklearn(X, y):
    """
    Entrena un modelo de regresión lineal múltiple usando todas las muestras.
    """
    model = LinearRegression()
    model.fit(X, y)
    y_pred = model.predict(X)
    mse = mean_squared_error(y, y_pred)
    r2 = r2_score(y, y_pred)
    return model, mse, r2, y_pred
