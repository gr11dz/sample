from core.models import User

from django.contrib.auth.hashers import make_password, check_password

CODES = {
    "REPATED-USERNAME": 100,
    "INVALID-PASSWORD": 101,
    "USERNAME-NOT-FOUND": 102,

    "SUCESS": 200,
    "USERNAME-FOUND": 201,
}


class UserManager:

    def __validate_username(self, USERNAME: str) -> int:
        usernames = User.objects.all().values("us_username")

        for iter in usernames:
            if USERNAME == iter["us_username"]:
                return CODES["USERNAME-FOUND"]
            
        return CODES["USERNAME-NOT-FOUND"]

    def __valiate_password(self, username: str, password: str) -> int:
        user = User.objects.filter(
            us_username = username
        ).first()
        if user is None:
            return CODES["USERNAME-NOT-FOUND"]
        
        if check_password(password, user.us_password):
            return CODES["SUCESS"]
        else:
            return CODES["INVALID-PASSWORD"]

    def create(self, data: dict) -> int:
        if self.__validate_username(data["username"]) == CODES["USERNAME-FOUND"]:
            return CODES["REPATED-USERNAME"]
        
        User.objects.create(
            us_firstname = data["firstname"],
            us_lastname = data["lastname"],
            us_username = data["username"],
            us_password = make_password(data["password"])
        )
        return CODES["SUCESS"]
    
    def validate_user(self, data: dict) -> bool:
        if self.__validate_username(data["username"]) == CODES["USERNAME-NOT-FOUND"]:
            return None
        
        result = self.__valiate_password(data["username"], data["password"])
        if result == CODES["USERNAME-FOUND"] or result == CODES["INVALID-PASSWORD"]:
            return False
        else:
            return True
        
        