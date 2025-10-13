import email
from email.parser import HeaderParser

# Use raw string for file path or escape backslashes
with open(r'D:\BE\LP4\email.eml', 'r', encoding='utf-8', errors='ignore') as f:
    msg = email.message_from_file(f)

# Parse headers
parser = HeaderParser()
headers = parser.parsestr(msg.as_string())

print('Headers Found:\n')
for i, (key, value) in enumerate(headers.items(), start=1):
    print(f"{i}. {key}: {value}")

# Example: extract SPF or DKIM related header if present
spf = headers.get('Received-SPF', 'Not Found')
dkim = headers.get('DKIM-Signature', 'Not Found')

print('\n-----------------------------------')
print(f'SPF Header: {spf}')
print(f'DKIM Header: {dkim}')
print('-----------------------------------')
