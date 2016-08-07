/**
 * Created by proudzhu on 7/31/16.
 */
public class ChicagoStyleVeggiePizza extends Pizza {
    public ChicagoStyleVeggiePizza() {
        name = "Chicago Style Deep Dish Veggie Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";

        toppings.add("Shredded Mozzarella Veggie");
    }

    void cut() {
        System.out.println("Cutting the pizza into square slices");
    }
}
