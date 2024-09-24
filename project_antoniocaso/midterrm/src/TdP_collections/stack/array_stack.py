class Empty(Exception):
  pass

class ArrayStack:
  """Implementazione di ADT Stack che utilizza un oggetto list di Python per la memorizzazione."""

  def __init__(self):
    """Crea uno stack vuoto."""
    self._data = []                       # instanza di list non pubblica

  def __len__(self):
    """Restituisce il numero di elementi nello stack."""
    return len(self._data)

  def is_empty(self):
    """Restituisce True se lo stack è vuoto."""
    return len(self._data) == 0

  def push(self, e):
    """Aggiunge l'elemento e al top dello stack."""
    self._data.append(e)                  # il nuovo elemento è aggiunto in coda alla list

  def top(self):
    """Restituisce (m anon rimuove) l'elemento al top dello stack.
       Raise Empty exception se lo stack è vuoto."""
    if self.is_empty():
      raise Empty('lo stack è vuoto')
    return self._data[-1]                 # legge l'ultimo elemento della list

  def pop(self):
    """Rimuove e restituisce l'elemento al top dello stack.
       Raise Empty exception se lo stack è vuoto."""
    if self.is_empty():
      raise Empty('lo stack è vuoto')
      # print("lo stack è vuoto")
    return self._data.pop()               # rimuove l'ultimo elemento della list

