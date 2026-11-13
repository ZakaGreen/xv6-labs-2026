[English](README.md) · [Slovenčina](README.sk.md) · [Русский](README.ru.md)

# xv6 — čo sa deje pod povrchom

Moje laboratórne úlohy z operačných systémov na **FEI STU**, založené na **výučbovom operačnom systéme xv6 pre RISC-V**.

Smerníkom a štruktúram v C som začal oveľa lepšie rozumieť, keď som si naštudoval fungovanie pamäte. Tieto úlohy mi umožňujú skúmať súvisiace témy v malom operačnom systéme: procesy, systémové volania, tabuľky stránok a pasce.

Zadania spravujem na [GitLabe](https://gitlab.com/ilushkalubotin/xv6-xliubotin-2026). Táto kópia na GitHube ich spája s mojimi ďalšími projektmi a zachováva existujúcu históriu vetiev.

## Prehľad laboratórnych úloh

Každá vetva predstavuje samostatný stav zadania. Tabuľka opisuje prácu zachytenú v importovanej histórii.

| Vetva | Oblasť |
| --- | --- |
| [util](https://github.com/ZakaGreen/xv6-labs-2026/tree/util) | Programy v používateľskom priestore, procesy a rúry. |
| [syscall](https://github.com/ZakaGreen/xv6-labs-2026/tree/syscall) | Systémové volania vrátane ich zachytávania a úloh so sandboxom. |
| [pgtbl](https://github.com/ZakaGreen/xv6-labs-2026/tree/pgtbl) | Tabuľky stránok a pamäť procesov. |
| [traps](https://github.com/ZakaGreen/xv6-labs-2026/tree/traps) | Výpis zásobníka volaní jadra, `sigalarm` a `sigreturn`. |
| [lock](https://github.com/ZakaGreen/xv6-labs-2026/tree/lock) | Začaté, zatiaľ rozpracované zadanie so zámkami. |

Vetva `main` pridáva tento sprievodný text k stavu vetvy `util`. Päť vetiev s úlohami zachováva pôvodné commity. Ide o kópiu stavu GitLabu v čase publikovania, nie o automaticky synchronizované zrkadlo.

## Lokálne preskúmanie

```bash
git clone https://github.com/ZakaGreen/xv6-labs-2026.git
cd xv6-labs-2026
git switch util
make qemu
```

Zostavenie vyžaduje vhodný toolchain RISC-V a QEMU s podporou RISC-V. Odkazy na nástroje sú v pôvodnom [README projektu xv6](README). Pri výbere vetvy a spúšťaní kontrol sa riaďte príslušným zadaním. Zostavenie ani hodnotiace testy úloh neboli pri tomto importe do portfólia znova spustené.

## Pôvod kódu

Samotné xv6 je dielom pôvodných autorov z MIT a ďalších prispievateľov. Mojím príspevkom sú školské úlohy FEI STU zaznamenané v študentských commitoch.

Pôvodná [licencia](LICENSE), README a história sú zachované. Zdrojom školských zadaní zostáva repozitár na GitLabe.

[Späť na môj profil](https://github.com/ZakaGreen)
