import { Component, OnInit } from '@angular/core';
import {GenericService} from '../generic.service';
import {ActivatedRoute, Router} from '@angular/router';

@Component({
  selector: 'app-update-recipe',
  templateUrl: './update-recipe.component.html',
  styleUrls: ['./update-recipe.component.css']
})
export class UpdateRecipeComponent implements OnInit {

  constructor(private service: GenericService, private router: Router, private route: ActivatedRoute) { }

  ngOnInit(): void {
  }

  updateRecipe(name: string, type: string, author: string, ingredients: string, instructions: string, image: string): void {
    const id = this.route.snapshot.queryParams['id'];
    this.service.updateRecipe(id, name, type, author, ingredients, instructions, image).subscribe(() => {
      this.router.navigate(['showRecipes']).then(_ => {
      });
    });
  }

  onCancel(): void {
    this.router.navigate(['showRecipes']).then(_ => {
    });
  }

}