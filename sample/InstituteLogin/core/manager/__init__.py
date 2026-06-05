from.user_manager import UserManager


SERVICE_MAP = {
    "user": UserManager
}

class Dispatcher:
    @staticmethod
    def get(service_name):
        service = SERVICE_MAP.get(service_name.lower())
        if not service:
            return None
        return service()