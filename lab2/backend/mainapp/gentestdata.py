import random
import datetime
from decimal import Decimal

import faker
from django.db import transaction

from .models import Book

fk = faker.Faker()


def gentestdata():
    with transaction.atomic():
        for _ in range(200):
            book = Book(
                title=fk.sentence(nb_words=4),
                author=fk.name(),
                year=random.randint(1900, 2025),
                price=Decimal(str(round(random.uniform(100, 5000), 2))),
                is_available=random.random() > 0.3,
                description=fk.text(max_nb_chars=200),
            )
            book.save()
    print('OK gentestdata()')