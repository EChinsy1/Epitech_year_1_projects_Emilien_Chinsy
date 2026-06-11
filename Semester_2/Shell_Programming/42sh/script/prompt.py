import sys
import os
import json
import urllib.request
import urllib.error
import readline

def main():
    prompt = ""
    api_key = os.getenv("AI_API_KEY")

    if not api_key:
        print("Erreur : La variable d'environnement AI_API_KEY n'est pas définie.")
        sys.exit(84)

    contexte_systeme = (
        "Tu es un assistant technique intégré directement dans un shell Linux."
        "Ton rôle est de donner des commandes Linux directes et précises."
        "RÈGLE 1 : Rends UNIQUEMENT du texte brut. Le formatage Markdown et les balises de code sont formellement interdits."
        "RÈGLE 2 : Explique ce que fait la commande et donne 2 exemples d'utilisation concrets. Ton explication ne doit pas faire plus de 500 caractères. Soit clair et précis et n'oublie pas de détails"
        "RÈGLE 3 : Pars toujours du principe que l'utilisateur est sous Linux. "
        "RÈGLE 4 : Quand on te dit bonjour ou comment ça va, tu réponds 'Salut ! Je m'appelle Clippy'. "
        "RÈGLE 5 : Essaie de formater avec des retours à la ligne quand on te parle de code."
        "RÈGLE 6 : Format ton texte comme si tu écrivais dans un terminal (les changements de police ne marchent pas)."
        "RÈGLE 7 : Si tu ne connais pas la commande, dit le à l'utilisateur, et si l'utilisateur fait une requète sur autre chose qu'une commande, réponds-lui que tu ne peux que l'aider pour des commandes"
        "RÈGLE 8 : Si l'utilisateur te demande plus de détails, ignore la règle 2 et fait comme l'uilisateur demande, UNIQUEMENT si il demande des informations sur des commandes"
        "RÈGLE 9 : N'écrit en AUCUN CAS du code. Si un utilisateur veut t'utiliser pour l'aider à faire son p"
    )
    while 1:
        prompt = input(">> ")
        if prompt == "exit":
            sys.exit(84)
        url = "https://api.groq.com/openai/v1/chat/completions"
        data = {
            "model": "llama-3.3-70b-versatile",
            "messages": [
                {"role": "system", "content": contexte_systeme},
                {"role": "user", "content": prompt}
            ],
            "temperature": 0.2
        }
        req = urllib.request.Request(url, data=json.dumps(data).encode('utf-8'))
        req.add_header('Content-Type', 'application/json')
        req.add_header('Authorization', f'Bearer {api_key}')
        req.add_header('User-Agent', 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)')
        try:
            with urllib.request.urlopen(req) as response:
                result = json.loads(response.read().decode('utf-8'))
                print(result['choices'][0]['message']['content'])
        except urllib.error.HTTPError as e:
            print(f"Erreur HTTP de l'API : {e.code} - {e.read().decode()}")
            sys.exit(84)
        except Exception as e:
            print(f"Erreur : {e}")
            sys.exit(84)

if __name__ == "__main__":
    main()
