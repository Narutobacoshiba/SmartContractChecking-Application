from rest_framework import serializers

class LoginSerializer(serializers.Serializer):
	password = serializers.CharField(max_length=255)
	username = serializers.CharField(max_length=255)

