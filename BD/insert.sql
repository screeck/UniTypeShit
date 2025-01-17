-- Insert Clients
INSERT INTO Clients (Client_ID, Client_Name, Client_Email) VALUES (1, 'John Doe', 'johndoe@example.com');
INSERT INTO Clients (Client_ID, Client_Name, Client_Email) VALUES (2, 'Jane Smith', 'janesmith@example.com');
INSERT INTO Clients (Client_ID, Client_Name, Client_Email) VALUES (3, 'Carlos Ramirez', 'carlosramirez@example.com');

-- Insert Sellers
INSERT INTO Seller (Seller_ID, Seller_Name, Seller_Email) VALUES (1, 'SkinHub', 'support@skinhub.com');
INSERT INTO Seller (Seller_ID, Seller_Name, Seller_Email) VALUES (2, 'LootMarket', 'contact@lootmarket.com');
INSERT INTO Seller (Seller_ID, Seller_Name, Seller_Email) VALUES (3, 'TradeZone', 'info@tradezone.com');

-- Insert Skins
INSERT INTO Skin (Skin_ID, Skin_Name, Skin_Weapon, Skin_Rarity, Skin_Condition, Skin_Value, Seller_Seller_ID)
VALUES (1, 'AWP | Dragon Lore', 'AWP', 'CONTRABAND', 'FN', 15000.00, 1);
INSERT INTO Skin (Skin_ID, Skin_Name, Skin_Weapon, Skin_Rarity, Skin_Condition, Skin_Value, Seller_Seller_ID)
VALUES (2, 'AK-47 | Redline', 'AK-47', 'RESTRICTED', 'FT', 25.00, 2);
INSERT INTO Skin (Skin_ID, Skin_Name, Skin_Weapon, Skin_Rarity, Skin_Condition, Skin_Value, Seller_Seller_ID)
VALUES (3, 'M4A4 | Howl', 'M4A4', 'CONTRABAND', 'MW', 8000.00, 1);
INSERT INTO Skin (Skin_ID, Skin_Name, Skin_Weapon, Skin_Rarity, Skin_Condition, Skin_Value, Seller_Seller_ID)
VALUES (4, 'Glock-18 | Fade', 'Glock-18', 'COVERT', 'FN', 2000.00, 3);
INSERT INTO Skin (Skin_ID, Skin_Name, Skin_Weapon, Skin_Rarity, Skin_Condition, Skin_Value, Seller_Seller_ID)
VALUES (5, 'Desert Eagle | Blaze', 'Desert Eagle', 'COVERT', 'FN', 3500.00, 2);

-- Insert Invoices
INSERT INTO Invoice (Invoice_ID, Invoice_Date, Invoice_Value, Clients_Client_ID)
VALUES (1, TO_DATE('2025-01-01', 'YYYY-MM-DD'), 15525.00, 1);
INSERT INTO Invoice (Invoice_ID, Invoice_Date, Invoice_Value, Clients_Client_ID)
VALUES (2, TO_DATE('2025-01-03', 'YYYY-MM-DD'), 8030.00, 2);
INSERT INTO Invoice (Invoice_ID, Invoice_Date, Invoice_Value, Clients_Client_ID)
VALUES (3, TO_DATE('2025-01-03', 'YYYY-MM-DD'), 3500.00, 3);
INSERT INTO Invoice (Invoice_ID, Invoice_Date, Invoice_Value, Clients_Client_ID)
VALUES (4, TO_DATE('2025-01-05', 'YYYY-MM-DD'), 5500.00, 1);

-- Insert Invoice Details
INSERT INTO Invoice_Details (Invoice_Item, Invoice_Item_Count, Invoice_Item_Price_Sum, Skin_Skin_ID, Invoice_Invoice_ID)
VALUES (6, 1, 2000.00, 4, 4); -- Glock-18 | Fade
INSERT INTO Invoice_Details (Invoice_Item, Invoice_Item_Count, Invoice_Item_Price_Sum, Skin_Skin_ID, Invoice_Invoice_ID)
VALUES (7, 1, 3000.00, 5, 4); -- Desert Eagle | Blaze
INSERT INTO Invoice_Details (Invoice_Item, Invoice_Item_Count, Invoice_Item_Price_Sum, Skin_Skin_ID, Invoice_Invoice_ID)
VALUES (8, 1, 500.00, 6, 4);  -- P250 | Sand Dune

INSERT INTO Invoice_Details (Invoice_Item, Invoice_Item_Count, Invoice_Item_Price_Sum, Skin_Skin_ID, Invoice_Invoice_ID)
VALUES (1, 1, 15000.00, 1, 1);
INSERT INTO Invoice_Details (Invoice_Item, Invoice_Item_Count, Invoice_Item_Price_Sum, Skin_Skin_ID, Invoice_Invoice_ID)
VALUES (2, 1, 25.00, 2, 1);
INSERT INTO Invoice_Details (Invoice_Item, Invoice_Item_Count, Invoice_Item_Price_Sum, Skin_Skin_ID, Invoice_Invoice_ID)
VALUES (3, 1, 8000.00, 3, 2);
INSERT INTO Invoice_Details (Invoice_Item, Invoice_Item_Count, Invoice_Item_Price_Sum, Skin_Skin_ID, Invoice_Invoice_ID)
VALUES (4, 1, 2000.00, 4, 3);
INSERT INTO Invoice_Details (Invoice_Item, Invoice_Item_Count, Invoice_Item_Price_Sum, Skin_Skin_ID, Invoice_Invoice_ID)
VALUES (5, 1, 3500.00, 5, 3);
