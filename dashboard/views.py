# dashboard/views.py
import requests
from django.shortcuts import render
from django.http import JsonResponse

# Put your NodeMCU IP here (change if different)
NODEMCU_URL = "http://10.236.153.107/data"

def index(request):
    # main page with chart
    return render(request, "dashboard/index.html")

def nodemcu_proxy(request):
    """
    Simple server-side proxy to the NodeMCU /data endpoint.
    Useful to avoid CORS and let Django handle the fetch.
    """
    try:
        r = requests.get(NODEMCU_URL, timeout=3)
        r.raise_for_status()
        return JsonResponse(r.json(), safe=False)
    except Exception as e:
        return JsonResponse({"error": str(e)}, status=500)
