import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv')

df_media = df.groupby(["N", "Threads"]).agg({
    "Tempo(s)": "mean",
    "Primo(s) Encontrado(s)" : "first"
}).reset_index()

df_media.to_csv("results_mean.csv", index=False)
print("'results_mean.csv' salvo")

seq_t = df_media[df_media["Threads"] == 1][["N", "Tempo(s)"]].set_index("N")["Tempo(s)"]

def acc(lin):
    return seq_t[lin["N"]] / lin["Tempo(s)"]

def eff(lin):
    return lin["Aceleração"] / lin["Threads"]

df_media["Aceleração"] = df_media.apply(acc, axis=1)
df_media["Eficiência"] = df_media.apply(eff, axis=1)

df_media.to_csv("eff_acc.csv", index=False)
print("Aceleração e Eficiência calculadas e salvas em 'eff_acc.csv'")

Ns = sorted(df_media["N"].unique())

for m in ["Aceleração", "Eficiência"]:
    plt.figure(figsize=(8,6))
    for N in Ns:
        s = df_media[df_media["N"] == N]
        plt.plot(s["Threads"], s[m], marker="o", label=f"N={N}")

    plt.xlabel("Número de Threads")
    plt.ylabel(m)
    plt.title(f"{m} por Número de Threads")
    plt.legend()
    plt.grid(True)
    plt.xticks([1,2,4,8])
    plt.tight_layout()
    plt.savefig(f"{m.lower()}_por_threads.png")
    plt.show()
